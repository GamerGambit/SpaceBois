#include "ENUpdatePopup.h"

#include "ENUpdateConfig.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Text/SRichTextBlock.h"
#include "SWebBrowser.h"
#include "Interfaces/IPluginManager.h"

void ENUpdatePopup::OnBrowserLinkClicked(const FSlateHyperlinkRun::FMetadata& Metadata)
{
	const FString* URL = Metadata.Find(TEXT("href"));

	if (URL)
	{
		FPlatformProcess::LaunchURL(**URL, nullptr, nullptr);
	}
}

void ENUpdatePopup::Register()
{
	const FString PluginDirectory = IPluginManager::Get().FindPlugin(TEXT("ElectronicNodes"))->GetBaseDir();
	const FString UpdatedConfigFile = PluginDirectory + "/UpdateConfig.ini";
	const FString CurrentPluginVersion = "3.3";

	UE_LOG(LogTemp, Log, TEXT("[EN] %s"), *UpdatedConfigFile);

	UENUpdateConfig* ENUpdatePopupConfig = GetMutableDefault<UENUpdateConfig>();

	if (FPaths::FileExists(UpdatedConfigFile))
	{
		ENUpdatePopupConfig->LoadConfig(nullptr, *UpdatedConfigFile);
	}
	else
	{
		ENUpdatePopupConfig->SaveConfig(CPF_Config, *UpdatedConfigFile);
	}

	if (ENUpdatePopupConfig->PluginVersionUpdate != CurrentPluginVersion)
	{
		ENUpdatePopupConfig->PluginVersionUpdate = CurrentPluginVersion;
		ENUpdatePopupConfig->SaveConfig(CPF_Config, *UpdatedConfigFile);

		FCoreDelegates::OnPostEngineInit.AddLambda([]()
		{
			Open();
		});
	}
}

void ENUpdatePopup::Open()
{
	TSharedRef<SBorder> WindowContent = SNew(SBorder)
			.BorderImage(FCoreStyle::Get().GetBrush("ToolPanel.GroupBorder"))
			.Padding(FMargin(8.0f, 8.0f));

	TSharedPtr<SWindow> Window = SNew(SWindow)
				.AutoCenter(EAutoCenter::PreferredWorkArea)
				.SupportsMaximize(false)
				.SupportsMinimize(false)
				.SizingRule(ESizingRule::FixedSize)
				.ClientSize(FVector2D(600, 400))
				.Title(FText::FromString("Electronic Nodes"))
	[
		WindowContent
	];

	const FSlateFontInfo HeadingFont = FCoreStyle::GetDefaultFontStyle("Regular", 24);
	const FSlateFontInfo ContentFont = FCoreStyle::GetDefaultFontStyle("Regular", 12);

	TSharedRef<SVerticalBox> InnerContent = SNew(SVerticalBox)
		// Default settings example
		+ SVerticalBox::Slot()
		  .AutoHeight()
		  .Padding(10)
		[
			SNew(STextBlock)
			.Font(HeadingFont)
			.Text(FText::FromString("Electronic Nodes v3.3"))
		]
		+ SVerticalBox::Slot()
		  .FillHeight(1.0)
		  .Padding(10)
		[
			SNew(SBorder)
			.Padding(10)
			.BorderImage(FEditorStyle::GetBrush("ToolPanel.DarkGroupBorder"))
			[
				SNew(SScrollBox)
				+ SScrollBox::Slot()
				[
					SNew(SRichTextBlock)
					.Text(FText::FromString(R"(
<LargeText>Hello and thank you for using Electronic Nodes!</>

First thing first, if you've been enjoying using it, it would mean a lot if you could just drop <a id="browser" href="https://bit.ly/2U1YT8O">a small review on the marketplace page</> :). I also wanted to mention that I made another plugin to update the UE4 style called <a id="browser" href="https://bit.ly/2TolSKQ">Darker Nodes</>.

But let's keep it short, here are the cool new features of version 3.3!

<LargeText>Features</>

* Added a Force Outside option to Ribbon Style (<a id="browser" href="https://github.com/hugoattal/ElectronicNodes/issues/38">issue #38</>)
* Added experimental UE5 support (<a id="browser" href="https://github.com/hugoattal/ElectronicNodes/issues/39">issue #39</>)
* Added update popup (you're looking at it) (<a id="browser" href="https://github.com/hugoattal/ElectronicNodes/issues/41">issue #41</>)

<LargeText>Bug fixes</>

* Fix Manhattan alignment on Behavior Trees (<a id="browser" href="https://github.com/hugoattal/ElectronicNodes/issues/35">issue #35</>)
* Fix Global Settings save (<a id="browser" href="https://github.com/hugoattal/ElectronicNodes/issues/40">issue #40</>)

<a id="browser" href="https://github.com/hugoattal/ElectronicNodes#changelog">See complete changelog</>
)"))
					.TextStyle(FEditorStyle::Get(), "NormalText")
					.DecoratorStyleSet(&FEditorStyle::Get())
					.AutoWrapText(true)
					+ SRichTextBlock::HyperlinkDecorator(TEXT("browser"), FSlateHyperlinkRun::FOnClick::CreateStatic(&OnBrowserLinkClicked))
				]
			]
		]
		+ SVerticalBox::Slot()
		  .AutoHeight()
		  .Padding(10)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().FillWidth(1.0f)
			[
				SNew(SButton)
				.Text(FText::FromString("Leave a review <3"))
				.HAlign(HAlign_Center)
				.OnClicked_Lambda([]()
				{
					const FString URL = "https://bit.ly/2RPhNPl";
					FPlatformProcess::LaunchURL(*URL, nullptr, nullptr);

					return FReply::Handled();
				})
			]
			+ SHorizontalBox::Slot().AutoWidth()
			[
				SNew(SSpacer)
				.Size(FVector2D(20, 10))
			]
			+ SHorizontalBox::Slot().FillWidth(1.0f)
			[
				SNew(SButton)
				.Text(FText::FromString("Discover Darker Nodes"))
				.HAlign(HAlign_Center)
				.OnClicked_Lambda([]()
				{
					const FString URL = "https://bit.ly/3vqUdGE";
					FPlatformProcess::LaunchURL(*URL, nullptr, nullptr);

					return FReply::Handled();
				})
			]
			+ SHorizontalBox::Slot().AutoWidth()
			[
				SNew(SSpacer)
				.Size(FVector2D(20, 10))
			]
			+ SHorizontalBox::Slot().FillWidth(1.0f)
			[
				SNew(SButton)
				.Text(FText::FromString("Close this window"))
				.HAlign(HAlign_Center)
				.OnClicked_Lambda([Window]()
				{
					Window->RequestDestroyWindow();

					return FReply::Handled();
				})
			]
		];

	WindowContent->SetContent(InnerContent);
	Window = FSlateApplication::Get().AddWindow(Window.ToSharedRef());
}
